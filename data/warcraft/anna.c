// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿拉蕾[2;37;0m[2;37;0m", ({"alalei"}));        
        set("gender", "女性");                
        set("long", "无敌超人虎妹妹[2;37;0m
它是澹台璇玑的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "anna");
        set("owner_name", "澹台璇玑");
        set_temp("owner", "anna");
        set_temp("owner_name", "澹台璇玑");
        ::setup();
}
