// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m战[36m龙[2;37;0m[2;37;0m", ({"zlong"}));        
        set("gender", "女性");                
        set("long", "一只强大的远古$MAG$战$CYN$龙[2;37;0m
它是武当小子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wud");
        set("owner_name", "武当小子");
        set_temp("owner", "wud");
        set_temp("owner_name", "武当小子");
        ::setup();
}
