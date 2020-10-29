// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是小鱼的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wxxxx");
        set("owner_name", "小鱼");
        set_temp("owner", "wxxxx");
        set_temp("owner_name", "小鱼");
        ::setup();
}
