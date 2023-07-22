const kanjiList = require("./kanji.js").kanji;
const fetch = require("isomorphic-unfetch");
const parse = require("node-html-parser").parse;
const fs = require("fs");
const pattern = /\b\d+\b/;

const getStrokeCount = async kanji => {
    try {
        let strokeCountHtml = null;
        let count = 5;
        do {
            if (count == 0) {
                console.log(kanji, "failed")
                return Promise.resolve("");
            }
            let page = await fetch("https://jisho.org/search/%23kanji%20" + kanji);
            let pageRoot = await parse(await page.text());
            strokeCountHtml = await pageRoot.querySelector(".kanji-details__stroke_count");
            count--;
        } while (strokeCountHtml == null);
        let strokeCount = pattern.exec(strokeCountHtml.rawText);
        return Promise.resolve(strokeCount[0]);
    } catch (error) {
        console.log(error, kanji);
        return Promise.resolve(0);
    }
    
};

function sliceIntoChunks(arr, chunkSize) {
    const res = [];
    for (let i = 0; i < arr.length; i += chunkSize) {
        const chunk = arr.slice(i, i + chunkSize);
        res.push(chunk);
    }
    return res;
}

(async () => {
    let strokeCountList = [];
    let chunks = sliceIntoChunks(kanjiList, 200);
    for (let chunk of chunks) {
        const strokeCountPromises = chunk.map(async kanji => {
            return await getStrokeCount(kanji);
        });
        const strokeCounts = await Promise.all(strokeCountPromises);
        strokeCountList = strokeCountList.concat(strokeCounts);
        console.log(strokeCountList)
    }
    fs.writeFile("strokeCount.txt", strokeCountList.join("\n"), (err) => {
        if (err) throw err;
        console.log("success")
    })

})()