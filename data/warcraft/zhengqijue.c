// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m正七诀[2;37;0m[2;37;0m", ({"zqj"}));        
        set("gender", "男性");                
        set("long", "出差华山那书。[2;37;0m
它是七觉正的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zhengqijue");
        set("owner_name", "七觉正");
        set_temp("owner", "zhengqijue");
        set_temp("owner_name", "七觉正");
        ::setup();
}
