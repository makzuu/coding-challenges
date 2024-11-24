package main

import (
	"bufio"
	"log"
	"os"
	"strings"
	"unicode"
)

type countFunc func(string) int

func count(filename string, sf bufio.SplitFunc) int {
	f, err := os.Open(filename)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()
	sc := bufio.NewScanner(f)
	sc.Split(sf)
	cnt := 0
	for sc.Scan() {
		cnt++
	}
	if err := sc.Err(); err != nil {
		log.Fatal(err)
	}
	return cnt
}

func countBytes(filename string) int {
	if filename == "" {
		return countBytesFromStdin()
	}
	return count(filename, bufio.ScanBytes)
}

func countLines(filename string) int {
	if filename == "" {
		return countLinesFromStdin()
	}
	return count(filename, bufio.ScanLines)
}

func countWords(filename string) int {
	if filename == "" {
		return countWordsFromStdin()
	}
	return count(filename, bufio.ScanWords)
}

func countChars(filename string) int {
	if filename == "" {
		return countCharsFromStdin()
	}
	return count(filename, bufio.ScanRunes)
}

var fileContent []byte

func getLinesFromStdin() {
	if len(fileContent) > 0 {
		return
	}

	sc := bufio.NewScanner(os.Stdin)
	sc.Split(bufio.ScanBytes)

	for sc.Scan() {
		fileContent = append(fileContent, sc.Bytes()...)
	}
	if err := sc.Err(); err != nil {
		log.Fatalf("error while reading from stdin: %s", err)
	}
}

func countBytesFromStdin() int {
	getLinesFromStdin()
	return len(fileContent)
}

func countLinesFromStdin() int {
	getLinesFromStdin()
	s := string(fileContent)
	s = strings.TrimSuffix(s, "\n")
	lines := strings.Split(s, "\n")
	return len(lines)
}

func countWordsFromStdin() int {
	getLinesFromStdin()
	s := string(fileContent)

	wordCount := 0
	inWord := false
	for _, v := range s {
		if unicode.IsSpace(v) {
			if inWord {
				wordCount++
			}
			inWord = false
		} else {
			inWord = true
		}
	}

	return wordCount
}

func countCharsFromStdin() int {
	getLinesFromStdin()
	s := string(fileContent)
	charCount := 0
	for _, _ = range s {
		charCount++
	}
	return charCount
}

func defaultOptions(f *file) {
	f.counts["lines"] = countLines(f.filename)
	f.counts["words"] = countWords(f.filename)
	f.counts["bytes"] = countBytes(f.filename)
}
