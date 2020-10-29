// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m哈雷摩托车[2;37;0m[2;37;0m", ({"motor"}));        
        set("gender", "男性");                
        set("long", "哈雷摩托是由哈雷戴维森摩托车公司生产的摩托车品牌。[2;37;0m
它是寻宝小娘的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "find");
        set("owner_name", "寻宝小娘");
        set_temp("owner", "find");
        set_temp("owner_name", "寻宝小娘");
        ::setup();
}
