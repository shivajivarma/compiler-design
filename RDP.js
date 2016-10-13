// E -> E - E
// E -> E + E
// E -> E * E
// E -> E / E
// E -> (E)
// E -> i
/* ------------ */
// E -> F MinusE
// MinusE -> - E/ epsilon
// F -> G PlusF
// PlusF -> + F/ epsilon
// G -> H StarG
// StarG -> * G/ epsilon
// H -> I SlashH
// SlashH -> / H/ epsilon
// I -> (E)
// I -> i
/* ------------ */
var parser = (function() {

    var string;
    var len;
    var pos;


    function E() {
        if (F() == 0) return 0;
        if (MinusE() == 0) return 0;
        return 1;
    }

    function MinusE() {
        if (string[pos] == '-') {
            pos++;
            if (E() == 0) return 0;
        }
        return 1;
    }

    function F() {
        if (G() == 0) return 0;
        if (PlusF() == 0) return 0;
        return 1;
    }

    function PlusF() {
        if (string[pos] == '+') {
            pos++;
            if (F() == 0) return 0;
        }

        return 1;
    }

    function G() {
        if (H() == 0) return 0;
        if (StarG() == 0) return 0;
        return 1;
    }

    function StarG() {
        if (string[pos] == '*') {
            pos++;
            if (G() == 0) return 0;
        }

        return 1;
    }

    function H() {
        if (I() == 0) return 0;
        if (SlashH() == 0) return 0;
        return 1;
    }

    function SlashH() {
        if (string[pos] == '/') {
            pos++;
            if (H() == 0) return 0;
        }

        return 1;
    }

    function I() {
        if (string[pos] == '(') {
            pos++;
            if (E() == 0) return 0;
            if (string[pos] == ')') pos++;
            else return 0;
        } else if (string[pos] == 'i') {
            pos++;
        } else {
            return 0;
        }

        return 1;
    }

    return function validator(input) {
        string = input;
        len = string.length;
        pos = 0;
        if (E() == 0){ 
          return false
        } else if (pos < len) {
            return false;
        } else {
            return true;
        }
    }

})();
