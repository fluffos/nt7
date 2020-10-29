// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m千[1;33m年[1;34m文[1;35m珠[2;37;0m[2;37;0m", ({"ppp"}));        
        set("gender", "男性");                
        set("long", "一头来自蜀山峨眉修行千年的灵兽似猪非猪獠牙朱眼耳似蒲扇[2;37;0m
它是徐仙子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "oxp");
        set("owner_name", "徐仙子");
        set_temp("owner", "oxp");
        set_temp("owner_name", "徐仙子");
        ::setup();
}
