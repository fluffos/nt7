// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("童虎[2;37;0m[2;37;0m", ({"tong"}));        
        set("gender", "男性");                
        set("long", "童虎[2;37;0m
它是海公公的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "pxcode");
        set("owner_name", "海公公");
        set_temp("owner", "pxcode");
        set_temp("owner_name", "海公公");
        ::setup();
}
