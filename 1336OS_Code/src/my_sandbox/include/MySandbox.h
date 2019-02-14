#include "demo_framework/include/SandboxApplication.h"

class MySandBox : public SandboxApplication
{
public:
	MySandBox(void);

    virtual ~MySandBox(void);

    virtual void Initialize();

    virtual void Update();

private:
	MySandBox(const MySandBox&);

};

