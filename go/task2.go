package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func getString() string {
	fmt.Print("Введите строку: ")
	reader := bufio.NewReader(os.Stdin)
	s, _ := reader.ReadString('\n')
	return strings.TrimSpace(s)
}

func getTemplate() string {
	fmt.Print("Введите шаблон: ")
	reader := bufio.NewReader(os.Stdin)
	p, _ := reader.ReadString('\n')
	return strings.TrimSpace(p)
}

func isMatch(s, p string, sIndex, pIndex int) bool {
	if pIndex == len(p) {
		return sIndex == len(s)
	}

	if p[pIndex] == '*' {
		return (sIndex < len(s) && isMatch(s, p, sIndex+1, pIndex)) ||
			isMatch(s, p, sIndex, pIndex+1)
	}

	if sIndex == len(s) {
		return false
	}

	if p[pIndex] == '?' || p[pIndex] == s[sIndex] {
		return isMatch(s, p, sIndex+1, pIndex+1)
	}

	return false
}

func main() {
	s := getString()
	p := getTemplate()

	if isMatch(s, p, 0, 0) {
		fmt.Println("Совпадение по шаблону!")
	} else {
		fmt.Println("Текст не совпадает с шаблоном")
	}
}

