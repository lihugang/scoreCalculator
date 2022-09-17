Score Calculator

seat table location: '.seat-table' in current directory, format is like this '1 2 3 n 4 5 6', '1 2 3' is one group, 'n' stands for 'next row'
please config your own _SERVER_REQUEST_PATH and _SERVER_APP_KEY in your src/env/env.h
parse csv format:
[Title]
id, name, score1, score2, score3...
1,'pig',1,2,3
2,'piggy',4,5,6

please use utf-8 encoding

default output filename is 'result.txt'
you can use '--output-filename=xxx' in cli to set output filename
cli format: 'scl [csv_location] [--output-filename=xxx]'

This project is using the following librarys:
- cJSON https://github.com/DaveGamble/cJSON MIT LICENSE
- curl https://github.com/curl/curl https://github.com/curl/curl/blob/master/COPYING

this project is licensing on MIT LICENSE