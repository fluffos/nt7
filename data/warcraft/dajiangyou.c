// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("酱油瓶[2;37;0m[2;37;0m", ({"djy"}));        
        set("gender", "男性");                
        set("long", "酱油瓶[2;37;0m
它是打酱油的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dajiangyou");
        set("owner_name", "打酱油");
        set_temp("owner", "dajiangyou");
        set_temp("owner_name", "打酱油");
        ::setup();
}
