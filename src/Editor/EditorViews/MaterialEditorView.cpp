#include "MaterialEditorView.hpp"

MaterialEditorView::MaterialEditorView(Forge::Camera &camera, Forge::QtInputHandler &input)
	: RendererWidget(camera, input)
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
