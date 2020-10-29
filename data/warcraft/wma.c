// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"wmabb"}));        
        set("gender", "女性");                
        set("long", "小马[2;37;0m
它是武米啊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wma");
        set("owner_name", "武米啊");
        set_temp("owner", "wma");
        set_temp("owner_name", "武米啊");
        ::setup();
}
