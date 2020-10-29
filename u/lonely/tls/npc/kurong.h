int ask_xingyue(object who)
{
	object me,ob;
	mapping myfam;

	me=this_player();

	myfam = me->query("family");
	if (!myfam || myfam["family_name"] != "天龙寺") {
		command("knock "+(string)me->query("id"));
		command("say 你非我派弟子，也敢来滥竽充数!\n");
		return 1;
	}
	if (me->query_skill("buddhism", 1) < 180){
		command("pat "+(string)me->query("id"));
		command("say 你的佛法还需精进，这星月菩提目前是不适合你的!\n");
		return 1;
	}
	command("nod "+(string)me->query("id"));
	ob=present("xingyue puti",this_object());
	if(ob){
		ob->move(me);
		command("say 你这么勤奋修行，这佛门至宝就送你防身吧!\n");
	} else
		command("say 你这么勤奋修行，不错不错，可惜我已经把它送给你的师兄弟了。\n");
	return 1;
}

void attempt_apprentice(object ob)
{
	string old_name,new_name;
	mapping myfam;

	myfam = (mapping)ob->query("family");
	if (!myfam) return;
	if (myfam["family_name"] != "天龙寺") {
		command ("say 你不是天龙寺弟子，这话从何说起！\n");
		return;
	}
	if((int)ob->query_skill("buddhism",1)<140){
		command("say 我段家武功与佛学息息相关，我看"+RANK_D->query_respect(ob)+"的禅宗修为似乎不够？");
		return;
	}
	if((int)ob->query_skill("yiyang-zhi",1)<160){
		command("say 我天龙寺武功首推一阳指，我看"+RANK_D->query_respect(ob)+"似乎应在一阳指上多下点功夫。");
		return;
	}
	if((int)ob->query_skill("qiantian-yiyang",1)<160) {
		command("say 修练一阳指内功最为重要，我看"+RANK_D->query_respect(ob)+"似乎应在乾天一阳功上多下点功夫。");
		return;
	}
	if(!(ob->query("tls")) && !(ob->query_temp("tls_app"))){
		command("say 阿弥陀佛！请回吧，贫僧不轻易收出家弟子。");
		return;
	}
	if(ob->query("tls")&&((int)ob->query("shen") > 1000 || (int)ob->query("shen")+1000 <0 )){
		command("say 我天龙寺乃清修之地，依我看"+RANK_D->query_respect(ob)+"似乎红尘未了,不宜继续修行。");
		return;
	}

	command("smile");
	old_name = ob->query("name");
	if (ob->query("tls") && (string)ob->query("class") =="bonze"){
        	new_name="本"+old_name[1..1];
	}
	else{
		new_name="本"+old_name[0..0];
	}
	if (!ob->query("tls") || (string)ob->query("class")!="bonze"){
		command("say 贫僧只收出家弟子，今日老僧帮你剃度。");
		message_vision("$N双手合什，喃喃念道: \n",ob);
		message_vision("我闻浮屠道  中有解脱门  置心如止水  视身等浮云 \n",ob);
		message_vision("抖擞垢秽衣  度脱生死轮  胡为爱所苦  不去尚逡巡 \n",ob);
		message_vision("回念发弘愿  愿此见在身  只受过去报  不结未来恩 \n",ob);
		message_vision("誓以智慧水  永洗烦恼尘  不将恩爱子  再结烦忧根 \n",ob);
		message_vision("枯荣禅师伸出一只皮包骨头的瘦手在"+ob->query("name")+"的头上一按，顿时头发尽落。\n",ob);
	}
	ob->set("name",new_name);
	ob->set("class","bonze");
	ob->set("tls",1);
	command("chat 入我门来法名"+new_name);
	command("recruit " + ob->query("id") );
	command("chat 哈哈哈哈!");
	command("chat 老衲终于找到一个可传衣钵之人,真是可喜可贺!");
	return;
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	ob->set("class", "bonze");
}

int ask_dudan(object who)
{
	object me,ob_dan;
	mapping myfam;
	me=this_player();
	myfam = (mapping)me->query("family");
	if (!myfam || myfam["family_name"] != "天龙寺") {
		command("slap "+(string)me->query("id"));
		command("say 你非我派弟子，也敢来滥竽充数!\n");
		return 1;
	}
	if (me->query_skill("kurong-changong", 1) < 20){
		command("pat "+(string)me->query("id"));
		command("say 你的枯荣禅功根基不够，这毒丹我是不能给你吃的!\n");
		return 1;
	}
	if((int)me->query("dudan_given") < (int)(me->query_skill("kurong-changong", 1)/10)) {
		command("nod "+(string)me->query("id"));
		me->add("dudan_given",1);
		ob_dan = new("/d/tls/npc/obj/dudan");
		ob_dan->move(me);
		message_vision("$N获得一颗毒丹。\n",this_player());
		command("say 这是一颗毒丹，可是对于修炼枯荣禅功，极为有益，你这么勤奋练功就赠给你吧!\n");
		return 1;
	}
	else  {
		command("say 你现在还是好好修炼枯荣禅功，老想靠药物来增涨可是不行! \n");
		return 1;
	}
}

string ask_liumai2()
{
        object me,ob,*thing;
	mapping myfam;
	int i;
	ob=this_player();
	me=this_object();

	myfam = (mapping)ob->query("family");

	if (myfam["family_name"] != "天龙寺"||!ob->query("tls")||ob->query("class") != "bonze"){
		return "对不起，我不知道！\n";

	}
   if (ob->query("liumai_pass") && (ob->query_skill("liumai-shenjian",1) < 181)) {
		command ("nod "+ ob->query("id"));
		message_vision("枯荣长老一掌向地拍去，身后轰然移开一扇石门，$N看也不看，走了过去。\n", ob);
		thing = deep_inventory(ob);
		i = sizeof(thing);
		while (i--)
		if (thing[i]->is_character()) {
			message_vision("枯荣长老突然伸手一拦，道；你怎么带外人进洞？。\n", ob);
			me->set_leader(ob);
			remove_call_out("kill_ob");
			call_out("kill_ob", 0, me);
			return " ";
		}
		ob->move("/d/tls/pyd");
		return "";
	}
	if( ob->query_skill("yiyang-zhi",1) < 180 )
		return "你的一阳指修炼的这么差，还不回去好好练功!!\n";
	if (ob->query("max_neili") < 4500)
		return "你的内力修炼的这么差，还不回去好好练功!!\n";
	if (ob->query_skill("force", 1) < 200)
		return "你的内功修炼的这么差，还不回去好好练功!!\n";
	if (ob->query_temp("try_fight"))
		return "你不是正在接我的招吗？!\n";
	if (ob->query_temp("try"))
		return "如果你准备好了，请确定(try)。 \n";
	if (me->query_temp("try"))
		return "对不起，现在正有人在准备过招. \n";
	if (me->query_temp("try_fight"))
		return "对不起，现在我正忙着，你有什么要求一会儿再说. \n";
        if (ob->query_skill("liumai-shenjian",1) > 180){
		ob->set("quest/天龙八部/武功/liumai_update",1);
		return "你的六脉神剑修为已经登峰造级，老衲这里也不能给你什么帮助了，\n"+
			"你去找镇南王世子段誉吧，也许他能给你些帮助。";
	}
	else {
		command("say 依照天龙寺祖上传下规矩，" + RANK_D->query_respect(ob) + "你必须接下我十招不死不昏，才够资格进普云洞修习六脉神剑。");
		ob->set_temp("try",1);
		me->set_temp("try",1);
		call_out("wait", 1, me, 0);
		return "如果你准备好了接招，请确定（try)。\n";
	}
}

void init()
{
	object me;
	me = this_player();
	::init();
	if (interactive(me) && living(me)) {
	 	if(me->query(QUESTDIR2+"start")&& !me->query(QUESTDIR2+"over"))
    {
    	command("look "+me->query("id"));
    	command("touch "+me->query("id"));
    	command("say 有这位大侠帮忙，本寺当可高枕无忧了。");
    }
	}
	add_action("do_yes", "try");
	add_action("do_kill", "kill");
	add_action("do_kill", "tk");
	add_action("do_kill", "teamkill");
	add_action("do_kill", "hit");
}

int do_kill(string arg)
{
	object ob,ob2;
	object me = this_player();
	ob2 = this_object();

	if (!arg) return 0;
	ob = present(arg, environment(me));

	if (ob == this_object() || ob == me) return 0;
	if (!ob || !ob->is_character()) return 0;

	if (ob->query("family/family_name") == "天龙寺") {
		if (me->query("family/family_name") == "天龙寺") {
			message_vision(ob2->name()+"向$N沉声喝道：出家人戒杀生，怎么连自己的同门都杀？！\n", me);
		}
		else {
			message_vision(ob2->name()+"向$N沉声喝道：大胆狂徒，居然来天龙寺行凶！\n", me);
			kill_ob(me);
		}
		me->set("vendetta/天龙寺", 1);
		return 1;
	}
	return 0;
}

int do_yes()
{
	object me,ob,room;
	ob = this_player();
	me = this_object();

	if( !ob->query_temp("try")) return 0;

	message_vision("$N单掌一立，沉声说道：“请”。\n",ob );
	set("max_jing",3000);
	set("jing",3000);
	set("eff_jingli",3000);
	set("max_qi",5000);
	set("qi",5000);
	set("jiali",100);
	set("neili",8000);
	set("max_neili",8000);
	command("yun rong");
	if(!( room = find_object("/d/tls/lsy" )) )
		room = load_object("/d/tls/lsy");
	room->delete("exits");
	ob->delete_temp("try");
	me->delete_temp("try");
	me->set_temp("try_fight",1);
	ob->set_temp("try_fight",1);
	call_out("fighting",  3, me, ob, 0);
	message_vision("枯荣大师双掌合什，躬身一揖，恭恭敬敬的道：“请指教。”\n",ob);
	return 1;
}

void waiting(object me, int wait_time)
{
	object fighter;

	if( wait_time >= 150 ) {
		say( "枯荣大师说道：看来你不打算接我十招了！\n\n");
		call_out("do_recover", 0, me);
		return;
	}
	if( !objectp( fighter = present( me->query_temp("fight"), environment(me) ) ) ){
		call_out("waiting", 1, me, wait_time + 1);
		return;
	}
}

void fighting(object me, object fighter, int count)
{
	object room;

	if (!fighter || !living(fighter) || environment(fighter)!=environment(me)) {
		if(!( room = find_object("/d/tls/lsy" )) )
                room = load_object("/d/tls/lsy");
		if( objectp(fighter)) {
			fighter->delete_temp("try_fight");
			fighter->delete_temp("beat_count");
		}
		me->delete_temp("try_fight");
		room->set("exits/out","/d/tls/songlin-1");
                command("chat* 摇了摇头，说道：想不到... 唉！");
		command("sigh");
		return;
	}
	else if (count <10) {
		if (interactive(fighter) && fighter->query_temp("try_fight") && living(fighter))
	 		COMBAT_D->do_attack(this_object(), fighter, query_temp("weapon"), random(2)?1:2);
	 	count++;
		call_out("fighting", 2, me, fighter, count);
	}
	else call_out("do_congra", 3, me, fighter);
}

void do_congra(object me, object fighter)
{
	int i;
	object room,*thing;

	if(!( room = find_object("/d/tls/lsy" )) )
		room = load_object("/d/tls/lsy");
	fighter->delete_temp("try_fight");
	fighter->set("liumai_pass",1);
	me->delete_temp("try_fight");
	command("smile");
        command("say 恭喜，恭喜，你技艺青出于蓝胜于蓝，可以修习本寺神功六脉神剑,你去吧。\n");
	room->set("exits/out","/d/tls/songlin-1");
	message_vision(HIY"\n枯荣长老一掌向地拍去，身后轰然移开一扇石门，$N看也不看，走了过去。\n"NOR,fighter);

        thing = deep_inventory(fighter);
	i = sizeof(thing);
	while (i--)
	if (thing[i]->is_character()) {
		message_vision("枯荣长老突然伸手一拦，道；你怎么带外人进洞？。\n", fighter);
		me->set_leader(fighter);
		remove_call_out("kill_ob");
		call_out("kill_ob", 0, me);
		return;
	}
	fighter->move("/d/tls/pyd");
	return;
}
