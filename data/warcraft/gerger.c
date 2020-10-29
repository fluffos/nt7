// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"haha"}));        
        set("gender", "男性");                
        set("long", "好捻on 9[2;37;0m
它是刈那的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gerger");
        set("owner_name", "刈那");
        set_temp("owner", "gerger");
        set_temp("owner_name", "刈那");
        ::setup();
}
