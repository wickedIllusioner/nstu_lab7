package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func getData() (int, int) {
	var n, m int
	fmt.Print("Введите число контейнеров (n) и их вместимость (m): ")
	_, err := fmt.Scan(&n, &m)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Ошибка чтения ввода:", err)
		os.Exit(1)
	}

	if n <= 0 || m <= 0 {
		fmt.Fprintln(os.Stderr, "Некорректный ввод. Вводимые значения должны быть строго положительными!")
		os.Exit(1)
	}
	return n, m
}

func fillItems() []int {
	var items []int
	fmt.Println("Введите высоту для каждого предмета (-1 для подтверждения): ")
	reader := bufio.NewReader(os.Stdin)
	input, _ := reader.ReadString('\n')
	parts := strings.Fields(input)

	for _, part := range parts {
		item, err := strconv.Atoi(part)
		if err != nil {
			continue
		}
		if item == -1 {
			break
		}
		if item >= 0 {
			items = append(items, item)
		}
	}
	return items
}

func fitCheck(containers []int, items []int, idx int) bool {
	if idx == len(items) {
		return true
	}

	for i := 0; i < len(containers); i++ {
		if containers[i] >= items[idx] {
			containers[i] -= items[idx]
			if fitCheck(containers, items, idx+1) {
				return true
			}
			containers[i] += items[idx]
		}
	}
	return false
}

func fitInit(n, m int, items []int) bool {
	containers := make([]int, n)
	for i := range containers {
		containers[i] = m
	}
	sort.Sort(sort.Reverse(sort.IntSlice(items)))
	return fitCheck(containers, items, 0)
}

func main() {
	n, m := getData()
	items := fillItems()

	if len(items) == 0 {
		fmt.Println("Вмещать нечего")
		os.Exit(0)
	}

	if fitInit(n, m, items) {
		fmt.Println("Предметы вмещаются")
	} else {
		fmt.Println("Увы, уместить не получится")
	}
}

