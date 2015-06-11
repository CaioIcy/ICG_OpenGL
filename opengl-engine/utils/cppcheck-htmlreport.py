#!/usr/bin/env python

# From https://github.com/danmar/cppcheck/tree/master/htmlreport

from __future__ import unicode_literals

import io
import sys
import optparse
import os
from collections import Counter

from pygments import highlight
from pygments.lexers import guess_lexer_for_filename
from pygments.formatters import HtmlFormatter
from xml.sax import parse as xml_parse
from xml.sax import SAXParseException as XmlParseException
from xml.sax.handler import ContentHandler as XmlContentHandler
from xml.sax.saxutils import escape

"""
Turns a cppcheck xml file into a browsable html report along
with syntax highlighted source code.
"""

STYLE_FILE = """
body {
    font: 13px Arial, Verdana, Sans-Serif;
    margin: 0;
    width: auto;
}

h1 {
    margin: 10px;
}

#footer > p {
    margin: 4px;
}

.error {
    background-color: #ffb7b7;
}

.error2 {
    background-color: #faa;
    border: 1px dotted black;
    display: inline-block;
    margin-left: 4px;
}

.inconclusive {
    background-color: #B6B6B4;
}

.inconclusive2 {
    background-color: #B6B6B4;
    border: 1px dotted black;
    display: inline-block;
    margin-left: 4px;
}

div.verbose {
    display: inline-block;
    vertical-align: top;
    cursor: help;
}

div.verbose div.content {
    display: none;
    position: absolute;
    padding: 10px;
    margin: 4px;
    max-width: 40%;
    white-space: pre-wrap;
    border: 1px solid black;
    background-color: #FFFFCC;
    cursor: auto;
}

.highlight .hll {
    padding: 1px;
}

#header {
    border-bottom: thin solid #aaa;
}

#menu {
    float: left;
    margin-top: 5px;
    text-align: left;
    width: 150px;
    height: 75%;
    position: fixed;
    overflow: auto;
    z-index: 1;
}

#menu_index {
    float: left;
    margin-top: 5px;
    padding-left: 5px;
    text-align: left;
    width: 200px;
    height: 75%;
    position: fixed;
    overflow: auto;
    z-index: 1;
}

#menu > a {
    display: block;
    margin-left: 10px;
    font: 12px;
    z-index: 1;
}

.highlighttable {
    background-color:white;
    z-index: 10;
    position: relative;
    margin: -10 px;
}

#content {
    background-color: white;
    -webkit-box-sizing: content-box;
    -moz-box-sizing: content-box;
    box-sizing: content-box;
    float: left;
    margin: 5px;
    margin-left: 10px;
    padding: 0 10px 10px 10px;
    width: 80%;
    padding-left: 150px;
}

#content_index {
    background-color: white;
    -webkit-box-sizing: content-box;
    -moz-box-sizing: content-box;
    box-sizing: content-box;
    float: left;
    margin: 5px;
    margin-left: 10px;
    padding: 0 10px 10px 10px;
    width: 80%;
    padding-left: 200px;
}

.linenos {
    border-right: thin solid #aaa;
    color: lightgray;
    padding-right: 6px;
}

#footer {
    border-top: thin solid #aaa;
    clear: both;
    font-size: 90%;
    margin-top: 5px;
}

#footer ul {
    list-style-type: none;
    padding-left: 0;
}
"""

HTML_HEAD = """
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Cppcheck - HTML report - %s</title>
    <link rel="stylesheet" href="style.css">
    <style>
%s
    </style>
    <script language="javascript">
      function getStyle(el,styleProp) {
        if (el.currentStyle)
          var y = el.currentStyle[styleProp];
        else if (window.getComputedStyle)
          var y = document.defaultView.getComputedStyle(el,null).getPropertyValue(styleProp);
        return y;
      }
      function toggle() {
        var el = this.expandable_content;
        var mark = this.expandable_marker;
        if (el.style.display == "block") {
          el.style.display = "none";
          mark.innerHTML = "[+]";
        } else {
          el.style.display = "block";
          mark.innerHTML = "[-]";
        }
      }
      function init_expandables() {
        var elts = document.getElementsByClassName("expandable");
        for (var i = 0; i < elts.length; i++) {
          var el = elts[i];
          var clickable = el.getElementsByTagName("span")[0];
          var marker = clickable.getElementsByClassName("marker")[0];
          var content = el.getElementsByClassName("content")[0];
          var width = clickable.clientWidth - parseInt(getStyle(content, "padding-left")) - parseInt(getStyle(content, "padding-right"));
          content.style.width = width + "px";
          clickable.expandable_content = content;
          clickable.expandable_marker = marker;
          clickable.onclick = toggle;
        }
      }
    </script>
  </head>
  <body onload="init_expandables()">
      <div id="header">
        <h1>Cppcheck report - %s: %s </h1>
      </div>
      <div id="menu" dir="rtl">
       <a href="index.html">Defect list</a>
       <br>
"""

HTML_HEAD_END = """
      </div>
      <div id="content">
"""

HTML_FOOTER = """
      </div>
      <div id="footer">
        <p>
         Cppcheck %s - a tool for static C/C++ code analysis</br>
         </br>
         Internet: <a href="http://cppcheck.sourceforge.net">http://cppcheck.sourceforge.net</a></br>
         IRC: <a href="irc://irc.freenode.net/cppcheck">irc://irc.freenode.net/cppcheck</a></br>
        <p>
      </div>
  </body>
</html>
"""

HTML_ERROR = "<span class='error2'>&lt;--- %s</span>\n"
HTML_INCONCLUSIVE = "<span class='inconclusive2'>&lt;--- %s</span>\n"

HTML_EXPANDABLE_ERROR = "<div class='verbose expandable'><span class='error2'>&lt;--- %s <span class='marker'>[+]</span></span><div class='content'>%s</div></div>\n"""
HTML_EXPANDABLE_INCONCLUSIVE = "<div class='verbose expandable'><span class='inconclusive2'>&lt;--- %s <span class='marker'>[+]</span></span><div class='content'>%s</div></div>\n"""

# escape() and unescape() takes care of &, < and >.
html_escape_table = {
    '"': "&quot;",
    "'": "&apos;"
}
html_unescape_table = {v:k for k, v in html_escape_table.items()}

def html_escape(text):
    return escape(text, html_escape_table)

class AnnotateCodeFormatter(HtmlFormatter):
    errors = []

    def wrap(self, source, outfile):
        line_no = 1
        for i, t in HtmlFormatter.wrap(self, source, outfile):
            # If this is a source code line we want to add a span tag at the
            # end.
            if i == 1:
                for error in self.errors:
                    if error['line'] == line_no:
                        try:
                            if error['inconclusive'] == 'true':
                                if error.get('verbose') and (error['verbose'] != error['msg']): # only print verbose msg if it really differs from actual message
                                    index = t.rfind('\n')
                                    t = t[:index] + HTML_EXPANDABLE_INCONCLUSIVE % (error['msg'], html_escape(error['verbose'].replace("\\012", '\n'))) + t[index+1:]
                                else:
                                    t = t.replace('\n', HTML_INCONCLUSIVE % error['msg'])
                        except KeyError:
                            if error.get('verbose') and (error['verbose'] != error['msg']):
                                index = t.rfind('\n')
                                t = t[:index] + HTML_EXPANDABLE_ERROR % (error['msg'], html_escape(error['verbose'].replace("\\012", '\n'))) + t[index+1:]
                            else:
                                t = t.replace('\n', HTML_ERROR % error['msg'])

                line_no = line_no + 1
            yield i, t


class CppCheckHandler(XmlContentHandler):

    """Parses the cppcheck xml file and produces a list of all its errors."""

    def __init__(self):
        XmlContentHandler.__init__(self)
        self.errors = []
        self.version = '1'
        self.versionCppcheck = ''

    def startElement(self, name, attributes):
        if name == 'results':
            self.version = attributes.get('version', self.version)

        if self.version == '1':
            self.handleVersion1(name, attributes)
        else:
            self.handleVersion2(name, attributes)

    def handleVersion1(self, name, attributes):
        if name != 'error':
            return

        self.errors.append({
            'file': attributes.get('file', ''),
            'line': int(attributes.get('line', 0)),
            'id': attributes['id'],
            'severity': attributes['severity'],
            'msg': attributes['msg']
        })

    def handleVersion2(self, name, attributes):
        if name == 'cppcheck':
            self.versionCppcheck = attributes['version']
        if name == 'error':
            try:
                self.errors.append({
                    'file': '',
                    'line': 0,
                    'id': attributes['id'],
                    'severity': attributes['severity'],
                    'msg': attributes['msg'],
                    'verbose': attributes.get('verbose'),
                    'inconclusive': attributes['inconclusive']
                })
            except KeyError:
                self.errors.append({
                    'file': '',
                    'line': 0,
                    'id': attributes['id'],
                    'severity': attributes['severity'],
                    'msg': attributes['msg'],
                    'verbose': attributes.get('verbose')
                })
        elif name == 'location':
            assert self.errors
            self.errors[-1]['file'] = attributes['file']
            self.errors[-1]['line'] = int(attributes['line'])

if __name__ == '__main__':
    # Configure all the options this little utility is using.
    parser = optparse.OptionParser()
    parser.add_option('--title', dest='title',
                      help='The title of the project.',
                      default='[project name]')
    parser.add_option('--file', dest='file',
                      help='The cppcheck xml output file to read defects '
                           'from. Default is reading from stdin.')
    parser.add_option('--report-dir', dest='report_dir',
                      help='The directory where the HTML report content is '
                           'written.')
    parser.add_option('--source-dir', dest='source_dir',
                      help='Base directory where source code files can be '
                           'found.')
    parser.add_option('--source-encoding', dest='source_encoding',
                      help='Encoding of source code.', default='utf-8')

    # Parse options and make sure that we have an output directory set.
    options, args = parser.parse_args()

    try:
        sys.argv[1]
    except IndexError:  # no arguments give, print --help
        parser.print_help()
        quit()

    if not options.report_dir:
        parser.error('No report directory set.')

    # Get the directory where source code files are located.
    source_dir = os.getcwd()
    if options.source_dir:
        source_dir = options.source_dir

    # Get the stream that we read cppcheck errors from.
    input_file = sys.stdin
    if options.file:
        if not os.path.exists(options.file):
            parser.error('cppcheck xml file: %s not found.' % options.file)
        input_file = io.open(options.file, 'r')

    # Parse the xml file and produce a simple list of errors.
    print('Parsing xml report.')
    try:
        contentHandler = CppCheckHandler()
        xml_parse(input_file, contentHandler)
    except XmlParseException as msg:
        print('Failed to parse cppcheck xml file: %s' % msg)
        sys.exit(1)

    # We have a list of errors. But now we want to group them on
    # each source code file. Lets create a files dictionary that
    # will contain a list of all the errors in that file. For each
    # file we will also generate a HTML filename to use.
    files = {}
    file_no = 0
    for error in contentHandler.errors:
        filename = error['file']
        if filename not in files.keys():
            files[filename] = {
                'errors': [], 'htmlfile': str(file_no) + '.html'}
            file_no = file_no + 1
        files[filename]['errors'].append(error)

    # Make sure that the report directory is created if it doesn't exist.
    print('Creating %s directory' % options.report_dir)
    if not os.path.exists(options.report_dir):
        os.mkdir(options.report_dir)

    # Generate a HTML file with syntax highlighted source code for each
    # file that contains one or more errors.
    print('Processing errors')
    decode_errors = []
    for filename, data in sorted(files.items()):
        htmlfile = data['htmlfile']
        errors = data['errors']

        lines = []
        for error in errors:
            lines.append(error['line'])

        if filename == '':
            continue

        source_filename = os.path.join(source_dir, filename)
        try:
            with io.open(source_filename, 'r', encoding=options.source_encoding) as input_file:
                content = input_file.read()
        except IOError:
            sys.stderr.write("ERROR: Source file '%s' not found.\n" %
                             source_filename)
            continue
        except UnicodeDecodeError:
            sys.stderr.write("WARNING: Unicode decode error in '%s'.\n" %
                             source_filename)
            decode_errors.append(source_filename[2:])  # "[2:]" gets rid of "./" at beginning
            continue

        htmlFormatter = AnnotateCodeFormatter(linenos=True,
                                              style='colorful',
                                              hl_lines=lines,
                                              lineanchors='line',
                                              encoding=options.source_encoding)
        htmlFormatter.errors = errors

        with io.open(os.path.join(options.report_dir, htmlfile),
                     'w') as output_file:
            output_file.write(HTML_HEAD %
                              (options.title,
                               htmlFormatter.get_style_defs('.highlight'),
                               options.title,
                               filename))

            for error in sorted(errors, key=lambda k: k['line']):
                output_file.write("<a href='%s#line-%d'> %s %s</a>" % (data['htmlfile'], error['line'], error['id'],   error['line']))

            output_file.write(HTML_HEAD_END)
            try:
                lexer = guess_lexer_for_filename(source_filename, '')
            except:
                sys.stderr.write("ERROR: Couldn't determine lexer for the file' " + source_filename + " '. Won't be able to syntax highlight this file.")
                output_file.write("\n <tr><td colspan='4'> Could not generated content because pygments failed to retrieve the determine code type.</td></tr>")
                output_file.write("\n <tr><td colspan='4'> Sorry about this.</td></tr>")
                continue

            if options.source_encoding:
                lexer.encoding = options.source_encoding

            output_file.write(
                highlight(content, lexer, htmlFormatter).decode(
                    options.source_encoding))

            output_file.write(HTML_FOOTER % contentHandler.versionCppcheck)

        print('  ' + filename)

    # Generate a master index.html file that will contain a list of
    # all the errors created.
    print('Creating index.html')

    with io.open(os.path.join(options.report_dir, 'index.html'),
                 'w') as output_file:

        stats_count = 0
        stats = []
        for filename, data in sorted(files.items()):
            for error in data['errors']:
                stats.append(error['id'])  # get the stats
                stats_count += 1

        stat_html = []
        # the following lines sort the stat primary by value (occurrences),
        # but if two IDs occur equally often, then we sort them alphabetically by warning ID
        try:
            cnt_max = Counter(stats).most_common()[0][1]
        except IndexError:
            cnt_max = 0

        try:
            cnt_min = Counter(stats).most_common()[-1][1]
        except IndexError:
            cnt_min = 0

        for occurrences in reversed(range(cnt_min, cnt_max+1)):
            for _id in [k for k, v in sorted(Counter(stats).items()) if v == occurrences]:
                stat_html.append("        " + str(dict(Counter(stats).most_common())[_id]) + " " + str(_id) + "<br/>\n")

        output_file.write(HTML_HEAD.replace('id="menu" dir="rtl"', 'id="menu_index"', 1).replace("Defect list", "Defect summary", 1) % (options.title, '', options.title, ''))
        output_file.write('       <p>\n' + '        ' + str(stats_count) + ' total<br/><br/>\n' + ''.join(stat_html) + '       </p>')
        output_file.write(HTML_HEAD_END.replace("content", "content_index", 1))
        output_file.write('       <table>\n')
        output_file.write(
            '       <tr><th>Line</th><th>Id</th><th>Severity</th><th>Message</th></tr>')
        for filename, data in sorted(files.items()):
            if filename in decode_errors:  # don't print a link but a note
                output_file.write("\n       <tr><td colspan='4'>%s</td></tr>" % (filename))
                output_file.write("\n       <tr><td colspan='4'> Could not generated due to UnicodeDecodeError</td></tr>")
            else:
                output_file.write(
                "\n       <tr><td colspan='4'><a href='%s'>%s</a></td></tr>" %
                (data['htmlfile'], filename))
                for error in sorted(data['errors'], key=lambda k: k['line']):
                    error_class = ''
                    try:
                        if error['inconclusive'] == 'true':
                            error_class = 'class="inconclusive"'
                            error['severity'] += ", inconcl."
                    except KeyError:
                        pass

                    if error['severity'] == 'error':
                        error_class = 'class="error"'
                    if error['id'] == 'missingInclude':
                        output_file.write(
                            '\n         <tr><td></td><td>%s</td><td>%s</td><td>%s</td></tr>' %
                            (error['id'], error['severity'], error['msg']))
                    else:
                        output_file.write(
                            "\n       <tr><td><a href='%s#line-%d'>%d</a></td><td>%s</td><td>%s</td><td %s>%s</td></tr>" %
                            (data['htmlfile'], error['line'], error['line'],
                             error['id'], error['severity'], error_class,
                             error['msg']))

        output_file.write('\n       </table>')
        output_file.write(HTML_FOOTER % contentHandler.versionCppcheck)

    if (decode_errors):
        sys.stderr.write("\nGenerating html failed for the following files: " + ' '.join(decode_errors))
        sys.stderr.write("\nConsider changing source-encoding (for example: \"htmlreport ... --source-encoding=\"iso8859-1\"\"\n")

    print('Creating style.css file')
    with io.open(os.path.join(options.report_dir, 'style.css'),
                 'w') as css_file:
        css_file.write(STYLE_FILE)

    print("\nOpen '" + options.report_dir + "/index.html' to see the results.")
