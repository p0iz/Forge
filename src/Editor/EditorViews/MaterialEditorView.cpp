#include "MaterialEditorView.hpp"

MaterialEditorView::MaterialEditorView(Forge::QtInputHandler &input, Forge::Camera& camera)
	: QtRenderer(input, camera)
{
}

MaterialEditorView::~MaterialEditorView()
{
}

void MaterialEditorView::setupScene()
{
	glClearColor(0,0,0,1.0f);
}

void MaterialEditorView::drawScene()
{
}

void MaterialEditorView::tearDownScene()
{
}
