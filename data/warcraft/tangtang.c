// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m狂暴白虎[2;37;0m[2;37;0m", ({"tangtangs"}));        
        set("gender", "女性");                
        set("long", "狂暴白虎[2;37;0m
它是唐棠的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "tangtang");
        set("owner_name", "唐棠");
        set_temp("owner", "tangtang");
        set_temp("owner_name", "唐棠");
        ::setup();
}
