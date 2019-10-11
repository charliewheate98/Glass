#pragma once

#include "Glass/Object.h"

class Mesh : public Glass::Object
{
private:
public:
	Mesh();
	~Mesh();

	virtual void Tick(float DeltaTime) override;
	virtual void Render() override;
};

