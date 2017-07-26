const FIVE_MINUTES_MS = 1000*60*5;

class BowlingScore {
    constructor(scoreChangeHandler) {
        this.pinsLastSeen = new Map();
        this.activePins = new Set();
        this.uprightPins = new Set();
        this.scoreChangeHandlers = [scoreChangeHandler];

        this.observePin = function (pinId) {
            this.pinsLastSeen.set(pinId, Date.now());
        };

        this.reportScoreChange = function () {
            let uprightAndActiveCount =
                [...this.activePins].filter((pin) => !this.uprightPins.has(pin)).length;
            this.scoreChangeHandlers.forEach((handler) => handler.acceptScore(uprightAndActiveCount));
        };
    }
};

BowlingScore.prototype.setUprightPinsAsActive = function () {
    this.activePins = new Set(this.uprightPins);
};

BowlingScore.prototype.pruneOldPins = function () {
    let now = Date.now().getTime();
    let timedOutPins =
        this.pinsLastSeen.entries()
            .filter((pin)  => now - pin[1].getTime() >=  FIVE_MINUTES_MS);
    timedOutPins.forEach(
        (pin) => {
            let pinId = pin[0];
            this.activePins.delete(pinId);
            this.uprightPins.delete(pinId);
            this.pinsLastSeen.delete(pinId);
        });
};

BowlingScore.prototype.pinStateChanged = function (pinId, pinFell) {
    this.observePin(pinId);
    if (pinFell) {
        this.uprightPins.delete(pinId);
    } else {
        this.uprightPins.add(pinId);
    }
    this.reportScoreChange();
};

module.exports = BowlingScore;
