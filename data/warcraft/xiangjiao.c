// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("芭蕉叶[2;37;0m[2;37;0m", ({"bajiaoye"}));        
        set("gender", "女性");                
        set("long", "美丽的叶子[2;37;0m
它是香蕉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiangjiao");
        set("owner_name", "香蕉");
        set_temp("owner", "xiangjiao");
        set_temp("owner_name", "香蕉");
        ::setup();
}
