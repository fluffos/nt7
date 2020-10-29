// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m飞龙在天[2;37;0m[2;37;0m", ({"lon"}));        
        set("gender", "男性");                
        set("long", "飞龙啊，在天上翱翔吧[2;37;0m
它是龙空无畏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "asword");
        set("owner_name", "龙空无畏");
        set_temp("owner", "asword");
        set_temp("owner_name", "龙空无畏");
        ::setup();
}
