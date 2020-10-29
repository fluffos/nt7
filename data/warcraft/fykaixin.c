// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "一个睡袋，江湖人士用来在野外睡觉用的。[2;37;0m
它是灵郭的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fykaixin");
        set("owner_name", "灵郭");
        set_temp("owner", "fykaixin");
        set_temp("owner_name", "灵郭");
        ::setup();
}
