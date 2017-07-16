let BowlingScore = require("../BowlingScore.js");

test('BowlingScore - Verify no pins active initially', () => {

    // Setup
    let reportedScores = [];
    let handler = {
        acceptScore: (score) => { reportedScores.push(score); }
    };
    let score = new BowlingScore(handler);

    // Execute
    score.pinStateChanged(1, false);
    score.pinStateChanged(2, false);
    score.pinStateChanged(1, true);
    score.pinStateChanged(2, true);

    // Execute
    // ... No score ever reported
    expect(reportedScores).toEqual([0,0,0,0])
});

test('BowlingScore - Falling and resetting pins affects score', () => {

    // Setup
    let reportedScores = [];
    let handler = {
        acceptScore: (score) => { reportedScores.push(score); }
    };
    let score = new BowlingScore(handler);
    score.pinStateChanged(1, false);
    score.pinStateChanged(2, false);
    reportedScores.length = 0;
    score.setUprightPinsAsActive();

    // Execute
    // ... Fall
    score.pinStateChanged(1, true);
    // ... Repeated fall
    score.pinStateChanged(1, true);
    // ... Another pin falls
    score.pinStateChanged(2, true);
    // ... Pin reset
    score.pinStateChanged(1, false);
    // ... Pin reset again
    score.pinStateChanged(1, false);

    // Verify
    expect(reportedScores).toEqual([1,1,2,1,1])
});

test('BowlingScore - Changing active pins prevents effects to score', () => {

    // Setup
    let reportedScores = [];
    let handler = {
        acceptScore: (score) => { reportedScores.push(score); }
    };
    let score = new BowlingScore(handler);
    score.pinStateChanged(1, false);
    score.pinStateChanged(2, false);
    reportedScores.length = 0;
    score.setUprightPinsAsActive();

    // Execute
    // ... Fall
    score.pinStateChanged(1, true);
    // ... Repeated fall
    score.pinStateChanged(1, true);
    // ... Another pin falls
    score.pinStateChanged(2, true);
    // ... Pin reset
    score.pinStateChanged(1, false);
    // ... Pin reset again
    score.pinStateChanged(1, false);

    // Verify
    expect(reportedScores).toEqual([1,1,2,1,1])
});
