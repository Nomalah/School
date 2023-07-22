const fs = require("fs");

fs.readFile("english_words.txt", (err, data) => {
    if (err) {
        console.error(err);
        console.error("Reading file failed, returning.");
        return;
    }
    let words = data.toString().split("\r\n");
    let tree = {
        letter: "",
        numOfChildren: 0,
        capped: false,
        children: {}
    };

    let treeBuilder = (wordToAdd, node) => {
        if (wordToAdd === "") {
            node.capped = true;
            return;
        } 
        
        node.capped = false;
          
        node.numOfChildren++;

        if (!node.children.hasOwnProperty(wordToAdd[0])) {
            node.children[wordToAdd[0]] = {
                letter: wordToAdd[0],
                numOfChildren: 0,
                capped: false,
                children: {}
            }
        }
        treeBuilder(wordToAdd.substring(1), node.children[wordToAdd[0]]);
    };
    for (let word of words) {
        treeBuilder(word, tree);
    }

    let correctChildrenCount = (node) => {
        node.numOfChildren = 0;

        if (node.capped) {
            return 1;
        }

        for (let child of Object.values(node.children)) {
            node.numOfChildren += correctChildrenCount(child);
        }
        
        return node.numOfChildren;
    }

    correctChildrenCount(tree);

    let graph = convertToDirectedGraph(tree.children["A"]);

    console.log(JSON.stringify(graph.nodes));
    //console.log(JSON.stringify(graph.edges));
});

const nodeDistanceMultiplier = 3000;

let convertToDirectedGraph = (tree) => {
    let dgEdges = [];
    let dgNodes = [];
    let graphGenerator = (node, parentId = null, depth = 0, window = { begin: 0, end: 2 * Math.PI }) => {
        let myId = dgNodes.length + 1;
        let targetAngle = (window.begin + window.end)/2;
        dgNodes.push({ id: myId, label: node.letter, x: Math.cos(targetAngle) * depth * nodeDistanceMultiplier, y: Math.sin(targetAngle) * depth * nodeDistanceMultiplier});
        if (parentId != null) {
            dgEdges.push({ from: parentId, to: myId });
        }
        let windowStart = window.begin;
        let windowSize = window.end - window.begin;
        for (let child of Object.values(node.children)) {
            let percentOfParent = child.numOfChildren / node.numOfChildren;
            let newWindowSize = windowSize * percentOfParent;
            graphGenerator(child, myId, depth + 1, { begin: windowStart, end: windowStart + newWindowSize });
            windowStart += newWindowSize;
        }
    };
    graphGenerator(tree);

    return { edges: dgEdges, nodes: dgNodes };
}