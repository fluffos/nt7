// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m无[1;34m限[1;35m打[1;32m宝[2;37;0m[2;37;0m", ({"amumu"}));        
        set("gender", "男性");                
        set("long", "我是一个专心打宝的好宠物[2;37;0m
它是小风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "naoo");
        set("owner_name", "小风");
        set_temp("owner", "naoo");
        set_temp("owner_name", "小风");
        ::setup();
}
