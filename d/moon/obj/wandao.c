//ken 1999.12.17

#include <ansi.h>
#include <weapon.h>
inherit BLADE;
void create()
{
	set_name(HIC "圆月弯刀" NOR, ({ "wandao" }) );
	set_weight(7000);
        set("value", 20000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "这是一把形状很奇特的刀，刀身仿佛有点弯曲。\n");
		set("material", "steel");
		set("wield_msg", "$N的$n突然出鞘，你根本就没有看见$N拔刀！\n");
		set("unwield_msg", "$N的$n已入鞘。\n");
	}
	init_blade(90);
	setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
	int dam ,pro;
        pro=query("force", victim);
	dam=query("force", me);
	if(dam > random(pro) )
	{
	victim->start_busy(1);
	return HIR "圆月弯刀迸发出霸道的刀气，席卷$n的全身！$n气为之窒，动弹不得！\n" NOR;
	}
}