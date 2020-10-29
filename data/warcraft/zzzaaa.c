// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"zzaaqqa"}));        
        set("gender", "女性");                
        set("long", "一只火麒麟[2;37;0m
它是偷偷偷偷的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zzzaaa");
        set("owner_name", "偷偷偷偷");
        set_temp("owner", "zzzaaa");
        set_temp("owner_name", "偷偷偷偷");
        ::setup();
}
