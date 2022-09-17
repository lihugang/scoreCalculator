const child = require('child_process');

child.exec('node make --debug --no-collect --no-download-seat-table --no-color --output-filename=scl-noNet-noColor-debug --watch');
child.exec('node make --release --no-collect --no-download-seat-table --no-color --output-filename=scl-noNet-noColor-release --watch');
child.exec('node make --debug --no-collect --no-download-seat-table --output-filename=scl-noNet-debug --watch');
child.exec('node make --no-collect --no-download-seat-table --output-filename=scl-noNet-release --release --watch');
child.exec('node make --no-collect --output-filename=scl-noCollect-debug --debug --watch');
child.exec('node make --no-collect --output-filename=scl-noCollect-release --release --watch');
child.exec('node make --no-collect --no-color --output-filename=scl-noCollect-noColor-debug --debug --watch');
child.exec('node make --no-collect --no-color --output-filename=scl-noCollect-noColor-release --release --watch');
child.exec('node make --output-filename=scl-debug --debug --watch');
child.exec('node make --output-filename=scl --release --watch');
child.exec('node make --no-color --output-filename=scl-noColor-debug --debug --watch');
child.exec('node make --no-color --output-filename=scl-noColor-release --release --watch');