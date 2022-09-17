const { exec } = require('child_process');
const fs = require('fs');

const IS_PRODUCTION = process.argv.indexOf('--production') !== -1 || process.argv.indexOf('--release') !== -1;
const IS_DEBUG = process.argv.indexOf('--debug') !== -1;
const IS_WATCH = process.argv.indexOf('--watch') !== -1;
const IS_NOCOLORFUL = process.argv.indexOf('--no-color') !== -1;
const outputPath = 'build';
let outputFilename = 'scl';

for (let i = 0; i < process.argv.length; i++) {
    if (process.argv[i].indexOf('--output-filename=') !== -1) outputFilename = process.argv[i].split('=')[1];
};

const IS_NO_COLLECT_FILE = process.argv.indexOf('--no-collect') !== -1;
const IS_NO_DOWNLOAD_SEAT_TABLE = process.argv.indexOf('--no-download-seat-table') !== -1;

if (!IS_PRODUCTION && !IS_DEBUG) {
    console.error('错误：请设置编译版本，--debug或--production参数');
    process.exit(0);
};
if (IS_PRODUCTION && IS_DEBUG) {
    console.error('错误：不能同时设置--production和--debug');
    process.exit(0);
};

var execCommand = '';

try {
    fs.mkdirSync(outputPath);
} catch (e) { };

if (IS_DEBUG) execCommand = `gcc -o ${outputPath}/${outputFilename} 
./src/index.c
-DDEBUG
-Wall -Wextra
-std=c99
-ggdb
-lcurl
-m32
`;
if (IS_PRODUCTION) execCommand = `gcc -o ${outputPath}/${outputFilename} 
./src/index.c
-DRELEASE
-std=c99
-funsigned-char
-lcurl
-Ofast
-m32`;
if (IS_NOCOLORFUL) execCommand += '\n-DNOCOLORFUL';
if (IS_NO_COLLECT_FILE) execCommand += '\n-DNOCOLLECTFILE';
if (IS_NO_DOWNLOAD_SEAT_TABLE) execCommand += '\n-DNODOWNLOADSEATTABLE';

console.log('---Score Calculator Makefile---');
console.log('Mode:', IS_PRODUCTION ? 'Production' : 'Development', '\n');
console.log('Output filename:', outputFilename);

const buildFile = () => new Promise((resolve, reject) => {
    const startTime = new Date().getTime();

    exec(execCommand.replaceAll('\n', ' '), (err, stdout, stderr) => {
        if (stderr.toLowerCase().indexOf('error') !== -1) {
            console.error(stderr);
            console.error('\n\033[7;31;47m编译错误！\033[0m');
            reject(err);
            return;
        }
        else {
            const endTime = new Date().getTime();
            console.log(stdout);
            console.log('\033[7;32;47m构建成功！\033[0m');
            console.log('\033[7;33;47m' + `用时 ${(endTime - startTime) / 1000}s` + '\033[0m');
            resolve();
        };
    });
});

((async () => {
    try {
        await buildFile();
    } catch (e) { };

    if (IS_WATCH) {
        console.log('\n\033[7;36;47m正在监听改变......\033[0m');

        fs.watch('./src', {
            recursive: true
        }, async (curr, prev) => {
            if (lock === 0) return;
            await getLock();
            console.clear();
            try {
                await buildFile();
            } catch (e) { };
            await releaseLock();

            console.log('\n\033[7;36;47m正在监听改变......\033[0m');
        });
    };
})());

let lock = 1;

async function getLock() {
    while (lock === 0) await sleep(500);
    lock = 0;
};

async function releaseLock() {
    lock = 1;
};

const sleep = (ts) => new Promise(resolve => setTimeout(resolve, ts));

