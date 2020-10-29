// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m火箭炮[2;37;0m[2;37;0m", ({"qjwjwxx"}));        
        set("gender", "男性");                
        set("long", "$MAG$火箭炮[2;37;0m
它是雨夜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qjwjwx");
        set("owner_name", "雨夜");
        set_temp("owner", "qjwjwx");
        set_temp("owner_name", "雨夜");
        ::setup();
}
