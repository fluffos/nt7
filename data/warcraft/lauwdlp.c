// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白雕[2;37;0m[2;37;0m", ({"lauwdlpbb"}));        
        set("gender", "女性");                
        set("long", "白雕[2;37;0m
它是不辣新娘的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lauwdlp");
        set("owner_name", "不辣新娘");
        set_temp("owner", "lauwdlp");
        set_temp("owner_name", "不辣新娘");
        ::setup();
}
