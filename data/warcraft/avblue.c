// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m小猫[2;37;0m[2;37;0m", ({"scat"}));        
        set("gender", "女性");                
        set("long", "$HIW$小猫[2;37;0m
它是蓝衣的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "avblue");
        set("owner_name", "蓝衣");
        set_temp("owner", "avblue");
        set_temp("owner_name", "蓝衣");
        ::setup();
}
