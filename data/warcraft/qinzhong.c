// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿斯顿[2;37;0m[2;37;0m", ({"asd"}));        
        set("gender", "男性");                
        set("long", "啊[2;37;0m
它是秦仲海的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qinzhong");
        set("owner_name", "秦仲海");
        set_temp("owner", "qinzhong");
        set_temp("owner_name", "秦仲海");
        ::setup();
}
