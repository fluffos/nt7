// surge-force.c 怒海狂涛

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return 1; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("surge-force", 1);
        
        if( query("can_perform/surge-force/new", me) )
        	return lvl * lvl / 100 * 15 * 38 / 200;
        	
        return lvl * lvl / 100  * 15 * 19 / 200;
}

int valid_learn(object me)
{
        if( query("gender", me) != "男性" && !query("yuanshen_level", me) )
		return notify_fail("你不具有男性的阳刚之气，无法修习怒海狂涛。\n");

	if ((int)me->query_skill("force", 1) < 150)
		return notify_fail("你的基本内功火候还不够，还不能修炼怒海狂涛。\n");

        if (me->query_str() < 45)
                return notify_fail("你的膂力不足，难以修习怒海狂涛。\n");

	if( query("can_perform/surge-force/new", me) )
	{
		if( query("int", me)<40 || query("con", me)<30 )
			return notify_fail("你先天属性不足，难以学成怒海狂涛。\n");
		
		if (me->query_skill("force", 1) < 1000)
			return notify_fail("你基本内功修为不足，无法修炼怒海狂涛。\n");
			
		if( query("max_neili", me)<35000 )
			return notify_fail("你内力修为不足，无法修炼怒海狂涛。\n");	
		
		if (me->query_skill("taoism", 1) < 1)
			return notify_fail("你道学心法修为不足，无法修炼怒海狂涛。\n");	
			
		if (me->query_skill("xuantie-jian", 1) < 1)
			return notify_fail("你玄铁剑法修为不足，无法修炼怒海狂涛。\n");					
			
		if (me->query_skill("martial-cognize", 1) < 1200)
			return notify_fail("你武学修养不足，无法修炼怒海狂涛。\n");		
			
		if (me->query_skill("jiuyin-shengong", 1) < 1 && 
		    me->query_skill("jiuyin-hamagong", 1))
		    	return notify_fail("你未曾练成过九阴真经，无法修炼怒海狂涛。\n");	
			
		if (me->query_skill("surge-force", 1) > me->query_skill("force", 1))
			return notify_fail("你基本内功修为不足，无法继续修炼怒海狂涛。\n");			
	}
		
	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("怒海狂涛只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"surge-force/" + func;
}

int difficult_level()
{
        //return 4000;
        return 100;
}
