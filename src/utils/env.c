#include "shared.h"
#include "env.h"

// user defined env vars
str env_lb_home = {0,0};

int env_init(void) {
	int res = LB_SUCCESS;
	char *ev = NULL;	
	
	// set load balancer home
	ev = getenv(LB_ENV_LOAD_BALANCER_HOME);
	if(ev == NULL) {
		
	} else {
		env_lb_home.len = LB_STR_LEN(ev);
		MALLOC(env_lb_home.s,env_lb_home.len);
		if(env_lb_home.s == NULL) {
			return LB_ERROR;
		}
		strncpy(env_lb_home.s,ev,env_lb_home.len);
	}

	return res;
}


