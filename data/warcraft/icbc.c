// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[32m中国工行[2;37;0m[2;37;0m", ({"icbca"}));        
        set("gender", "男性");                
        set("long", "第三方[2;37;0m
它是江非的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "icbc");
        set("owner_name", "江非");
        set_temp("owner", "icbc");
        set_temp("owner_name", "江非");
        ::setup();
}
