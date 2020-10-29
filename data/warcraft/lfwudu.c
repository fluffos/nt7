// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m蓝凤凰[2;37;0m[2;37;0m", ({"shengou"}));        
        set("gender", "女性");                
        set("long", "神仙狗[2;37;0m
它是凤五毒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lfwudu");
        set("owner_name", "凤五毒");
        set_temp("owner", "lfwudu");
        set_temp("owner_name", "凤五毒");
        ::setup();
}
