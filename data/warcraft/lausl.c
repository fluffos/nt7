// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m圣龙[2;37;0m[2;37;0m", ({"lauslbb"}));        
        set("gender", "女性");                
        set("long", "我的宝贝[2;37;0m
它是不毒邪龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lausl");
        set("owner_name", "不毒邪龙");
        set_temp("owner", "lausl");
        set_temp("owner_name", "不毒邪龙");
        ::setup();
}
