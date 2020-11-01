package main

import (
	"fmt"
	"math/rand"
	"time"
)

func getTime() string {
	return time.Now().Format("15:04:05.99999999")
}

func actionA(source <-chan int) <-chan int {
	result := make(chan int)

	go func() {
		defer close(result)

		for arg := range source {
			fmt.Print("time: ", getTime(), " in A: ", arg, "\n")
			value := arg * arg
			time.Sleep(100)
			fmt.Print("time: ", getTime(), " out A: ", value, "\n")
			result <- value
		}
	}()

	return result
}

func actionB(source <-chan int) <-chan int {
	result := make(chan int)

	go func() {
		defer close(result)

		for arg := range source {
			fmt.Print("time: ", getTime(), " in B: ", arg, "\n")
			value := arg * arg
			time.Sleep(2 * time.Second)
			fmt.Print("time: ", getTime(), " out B: ", value, "\n")
			result <- value
		}
	}()

	return result
}

func generate(n int) <-chan int {
	queue := make(chan int)

	go func() {
		defer close(queue)

		for i := 0; i < n; i++ {
			value := rand.Intn(100)
			fmt.Print("time: ", getTime(), " send: ", value, "\n")
			queue <- value
		}
	}()

	return queue
}

func main() {
	for res := range actionB(actionA(generate(20))) {
		fmt.Print("time: ", getTime(), " result: ", res, "\n")
	}
}
