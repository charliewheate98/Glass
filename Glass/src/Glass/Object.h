#pragma once

class Object
{
private:
public:
	Object() {}
	virtual ~Object() {}

	virtual void Tick(float DeltaTime) {}
	virtual void Render() {}
};

