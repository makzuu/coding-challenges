package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
)

type countFunc func (string) int

func countBytes(filename string) int {
	data, err := os.ReadFile(filename)
	if err != nil {
		log.Fatalf("Error reading file %v: %v", filename, err)
	}
	return len(data)
}

func countLines(filename string) int {
	f, err := os.Open(filename)
	if err != nil {
		fmt.Errorf("Error: opening file %v: %v", filename, err)
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	linesCount := 0
	for scanner.Scan() {
		linesCount++
	}
	if err = scanner.Err(); err != nil {
		log.Fatalln(err)
	}
	return linesCount
}

func countWords(filename string) int {
	f, err := os.Open(filename)
	if err != nil {
		fmt.Errorf("Error: opening file %v: %v", filename, err)
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	scanner.Split(bufio.ScanWords)
	wordsCount := 0
	for scanner.Scan() {
		wordsCount++
	}
	if err = scanner.Err(); err != nil {
		log.Fatalln(err)
	}
	return wordsCount
}

func countChars(filename string) int {
	f, err := os.Open(filename)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()
	scanner := bufio.NewScanner(f)
	scanner.Split(bufio.ScanRunes)
	charCount := 0
	for scanner.Scan() {
		charCount++
	}
	if err = scanner.Err(); err != nil {
		log.Fatal(err)
	}
	return charCount
}

func defaultOption(filename string) (int, int, int) {
	lineCount := countLines(filename)
	wordCount := countWords(filename)
	byteCount := countBytes(filename)

	return lineCount, wordCount, byteCount
}
