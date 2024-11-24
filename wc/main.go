package main

import (
	"fmt"
	"log"
	"os"
	"strings"
)

type file struct {
	filename string
	counts   map[string]int
}

func handleArgs(args []string) ([]file, []rune) {
	var options []rune
	var files []file
	for _, arg := range args {
		if strings.HasPrefix(arg, "-") {
			arg = strings.Trim(arg, "-")
			for _, r := range arg {
				options = append(options, r)
			}
		} else {
			files = append(files, file{filename: arg, counts: make(map[string]int)})
		}
	}
	return files, options
}

func printResults(files []file) {
	count := ""
	for _, file := range files {
		if v, ok := file.counts["lines"]; ok {
			count += fmt.Sprintf("%d ", v)
		}
		if v, ok := file.counts["words"]; ok {
			count += fmt.Sprintf("%d ", v)
		}
		if v, ok := file.counts["bytes"]; ok {
			count += fmt.Sprintf("%d ", v)
		}
		if v, ok := file.counts["chars"]; ok {
			count += fmt.Sprintf("%d ", v)
		}
		count += fmt.Sprintf("%s\n", file.filename)
	}
	fmt.Print(count)
}

func main() {
	files, options := handleArgs(os.Args[1:])

	if len(files) == 0 {
		files = append(files, file{filename: "", counts: make(map[string]int)})
	}

	if len(options) > 0 {
		for _, file := range files {
			for _, opt := range options {
				switch opt {
				case 'l':
					file.counts["lines"] = countLines(file.filename)
				case 'w':
					file.counts["words"] = countWords(file.filename)
				case 'c':
					file.counts["bytes"] = countBytes(file.filename)
				case 'm':
					file.counts["chars"] = countChars(file.filename)
				default:
					log.Printf("%c is not available option", opt)
				}
			}
		}
		printResults(files)

	} else {
		for _, file := range files {
			defaultOptions(&file)
		}
		printResults(files)
	}
}
