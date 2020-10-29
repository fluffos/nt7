// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大马[2;37;0m[2;37;0m", ({"dama"}));        
        set("gender", "男性");                
        set("long", "大马[2;37;0m
它是蚩尤的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "chiyou");
        set("owner_name", "蚩尤");
        set_temp("owner", "chiyou");
        set_temp("owner_name", "蚩尤");
        ::setup();
}
