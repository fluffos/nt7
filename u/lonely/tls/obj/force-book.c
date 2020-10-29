
inherit ITEM;

void create()
{
	set_name("线装经书", ({ "jingshu", "shu", "jing", "book" }));
	set_weight(200);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "本");
		set("long", "这是一本很旧的线装经书。封面写着四句偈语：有常无常 双树枯荣 南北西东 非假非空 \n");
    	set("value", 0);
		set("material", "paper");
	
	}
}
void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}
int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int jylevel; 
        int neili_lost;
        if (!(arg=="jing" ||arg=="book"))
        return 0;

        if (where->query("pigging")){
                write("你还是专心拱猪吧！\n");
                return 1;
        }
        if (me->is_busy()) {
                write("你现在正忙着呢。\n");
                return 1;
        }

        if( me->is_fighting() ) {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }

        if (!id(arg)) {	
                write("你要读什么？\n");
                return 1;
        }
       
        if( !me->query_skill("literate", 1) ){
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }
        
        if( (int)me->query("jing") < 15 ) {
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }
	if (me->query_skill("force",1)<80){
		write("你的内功基础没有打好，不能修练枯荣禅功。\n");
		return 1;
	}
       if (me->query_skill("qiantian-yiyang",1)<80){
		write("由于你的乾天一阳功不够火候，不能学习枯荣禅功。\n");
		return 1;
	}

	if (me->query_skill("qiantian-yiyang",1)<me->query_skill("kurong-changong",1)){
		write("由于你的乾天一阳功不够娴熟，不能再继续学习枯荣禅功。\n");
		return 1;
	}
	if( (int)me->query("neili") < neili_lost) {
		write("你内力不够，无法钻研这么高深的武功。\n");
                return 1;
        }
	if ((int)me->query_skill("buddhism",1)<(int)me->query_skill("kurong-changong",1))
	{
		write("你的禅宗心法修为不够，无法领会更高深的枯荣功。\n");
		return 1;
	}
        if(me->query_skill("kurong-changong",1)>40){
                write("你已经无法再从经书上领悟到什么了。\n");
                return 1;
        }
	neili_lost=(int)(me->query_skill("kurong-changong",1)/10);
        me->receive_damage("jing", 15);
	me->set("neili",(int)me->query("neili")-neili_lost);
	me->improve_skill("kurong-changong", (int)me->query_skill("literate", 1)/3+1);
	message("vision", me->name() + "拿着一本经书正在默默念着。\n", environment(me), me);
        write("你默诵经书，颇有心得。\n");
	return 1;
}
