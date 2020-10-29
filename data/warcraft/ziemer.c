// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凤飞九天[2;37;0m[2;37;0m", ({"zzzzz"}));        
        set("gender", "女性");                
        set("long", "一只朱雀[2;37;0m
它是风雪残楼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ziemer");
        set("owner_name", "风雪残楼");
        set_temp("owner", "ziemer");
        set_temp("owner_name", "风雪残楼");
        ::setup();
}
