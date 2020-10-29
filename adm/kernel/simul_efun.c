// #pragma optimize
// #pragma save_binary

#include <ansi.h>

private inherit __DIR__ "check_config";

#include "/adm/kernel/simul_efun/atoi.c"
#include "/adm/kernel/simul_efun/object.c"
#include "/adm/kernel/simul_efun/file.c"
#include "/adm/kernel/simul_efun/ntefun.c"
#include "/adm/kernel/simul_efun/chinese.c"
#include "/adm/kernel/simul_efun/gender.c"
#include "/adm/kernel/simul_efun/override.c"
#include "/adm/kernel/simul_efun/path.c"
#include "/adm/kernel/simul_efun/wizard.c"
#include "/adm/kernel/simul_efun/user.c"

// This must be after gender.c
#include "/adm/kernel/simul_efun/message.c"

// This is the utilitis
#include "/adm/kernel/simul_efun/util.c"

void create()
{
        seteuid(getuid());
        write("simul_efun loaded successfully.\n");
}
