package main

import (
	"fmt"
	"image/color"
	"log"
	"math"

	"github.com/hajimehoshi/ebiten/v2"
	"github.com/hajimehoshi/ebiten/v2/ebitenutil"
)

const (
	screenWidth  = 800
	screenHeight = 600
	maxDepth     = 12
)

type Game struct {
	whiteSquare *ebiten.Image
}

func (g *Game) init() {
	g.whiteSquare = ebiten.NewImage(1, 1)
	g.whiteSquare.Fill(color.White)
}

func (g *Game) drawPythagoreanTree(screen *ebiten.Image, positionX, positionY, size, angle float64, depth int, rColor int) {
	if depth == 0 {
		return
	}

	opts := &ebiten.DrawImageOptions{}

	opts.ColorM.Scale(float64(rColor)/255.0, 240.0/255.0, 0.0/255.0, 1.0)

	opts.GeoM.Scale(size, size)

	radAngle := angle * math.Pi / 180.0

	opts.GeoM.Translate(-size/2, -size)
	opts.GeoM.Rotate(radAngle)
	opts.GeoM.Translate(positionX, positionY)

	screen.DrawImage(g.whiteSquare, opts)

	relativeTopLeftX := -size / 2.0
	relativeTopLeftY := -size
	relativeTopRightX := size / 2.0
	relativeTopRightY := -size

	cosAngle := math.Cos(radAngle)
	sinAngle := math.Sin(radAngle)

	topLeftRotatedX := positionX + (relativeTopLeftX*cosAngle - relativeTopLeftY*sinAngle)
	topLeftRotatedY := positionY + (relativeTopLeftX*sinAngle + relativeTopLeftY*cosAngle)

	topRightRotatedX := positionX + (relativeTopRightX*cosAngle - relativeTopRightY*sinAngle)
	topRightRotatedY := positionY + (relativeTopRightX*sinAngle + relativeTopRightY*cosAngle)

	newSize := size / math.Sqrt(2.0)
	nextColor := rColor - 20

	g.drawPythagoreanTree(screen, topLeftRotatedX, topLeftRotatedY, newSize, angle-45, depth-1, nextColor)
	g.drawPythagoreanTree(screen, topRightRotatedX, topRightRotatedY, newSize, angle+45, depth-1, nextColor)
}

func (g *Game) Update() error {
	return nil
}

func (g *Game) Draw(screen *ebiten.Image) {
	screen.Fill(color.White)

	initialSize := 100.0
	initialAngle := 0.0
	initialColor := 255

	adjustedInitialPositionX := 400.0
	adjustedInitialPositionY := 500.0 - initialSize/2

	g.drawPythagoreanTree(screen, adjustedInitialPositionX, adjustedInitialPositionY, initialSize, initialAngle, maxDepth, initialColor)

	ebitenutil.DebugPrint(screen, fmt.Sprintf("FPS: %0.2f", ebiten.ActualFPS()))
}

func (g *Game) Layout(outsideWidth, outsideHeight int) (int, int) {
	return screenWidth, screenHeight
}

func main() {
	game := &Game{}
	game.init()

	ebiten.SetWindowSize(screenWidth, screenHeight)
	ebiten.SetWindowTitle("Pythagorean Tree (Go with Ebiten)")
	ebiten.SetVsyncEnabled(false)

	if err := ebiten.RunGame(game); err != nil {
		log.Fatal(err)
	}
}

