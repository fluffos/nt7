// treasury.c
/*********************
 *     帮派金库      *
 *                   *
 * 存钱默认为：coin  *
 * 取钱默认为：gold  *
 * [方便使用]        *
 *                   *
 *   by Find.        *
 *********************/

#define MAX_SAVE	100000000

protected mapping banghui_bank = ([]);

protected nosave string *valid_money = ({ "gold", "silver", "coin" });

protected varargs int save_to_treasury(int num, string money)
{
	int tmp, n;

	if(!intp(num) || (num <= 0) || (num > MAX_SAVE))
		return 0;

	if(!money)
		money = "coin";

	if(member_array(money, valid_money) == -1)
		return 0;

	if(!mapp(banghui_bank))
		banghui_bank = ([]);

	if(banghui_bank[money] >= MAX_SAVE)
		return 0;

	switch(money)
	{
		case "gold":
			if(undefinedp(banghui_bank["gold"]))
			{
				banghui_bank += ([ "gold" : num ]);
				return 1;
			}

			if(banghui_bank["gold"] + num > MAX_SAVE)
			{
				banghui_bank["gold"] = MAX_SAVE;
				return -(banghui_bank["gold"] + num - MAX_SAVE);
			}

			banghui_bank["gold"] += num;
			return 1;

		case "silver":
			if(undefinedp(banghui_bank["silver"]))
				banghui_bank += ([ "silver" : 0 ]);

			if( (tmp = banghui_bank["silver"] + num) > 100)
			{
				if(n = save_to_treasury(tmp/100, "gold") > 0)
					tmp %= 100;
				if(n < 0)
					tmp = abs(n)*100 + tmp%100;
			}

			if(tmp > MAX_SAVE)
			{
				banghui_bank["silver"] = MAX_SAVE;
				return -(tmp - MAX_SAVE);
			}

			banghui_bank["silver"] = tmp;
			return 1;

		case "coin":
			if(undefinedp(banghui_bank["coin"]))
				banghui_bank += ([ "coin" : 0 ]);

			if( (tmp = banghui_bank["coin"] + num) > 100)
			{
				if(n = save_to_treasury(tmp/100, "silver") > 0)
					tmp %= 100;
				if(n < 0)
					tmp = abs(n)*100 + tmp%100;
			}

			if(tmp > MAX_SAVE)
			{
				banghui_bank["coin"] = MAX_SAVE;
				return -(tmp - MAX_SAVE);
			}

			banghui_bank["coin"] = tmp;
			return 1;
	}

	return 0;
}

protected varargs int pay_from_treasury(int num, string money)
{
	int tmp, n;

	if( !intp(num)
	|| (num <= 0)
	|| (num > MAX_SAVE)
	|| !mapp(banghui_bank)
	|| !sizeof(banghui_bank) )
		return 0;

	if(!money)
		money = "gold";

	if(member_array(money, valid_money) == -1)
		return 0;

	switch(money)
	{
		case "gold":
			if(undefinedp(banghui_bank["gold"]) || (banghui_bank["gold"] < num))
				return 0;

			banghui_bank["gold"] -= num;
			return 1;

		case "silver":
			if(!undefinedp(banghui_bank["silver"]) && (banghui_bank["silver"] >= num))
			{
				banghui_bank["silver"] -= num;
				return 1;
			}

			n = num/100;
			if(num%100)
				n++;

			if(!pay_from_treasury(n, "gold"))
				return 0;

			if(tmp = n*100 - num)
			{
				if(undefinedp(banghui_bank["silver"]))
					banghui_bank += ([ "silver" : tmp ]);
				else
					banghui_bank["silver"] += tmp;
			}

			return 1;

		case "coin":
			if(!undefinedp(banghui_bank["coin"]) && (banghui_bank["coin"] >= num))
			{
				banghui_bank["coin"] -= num;
				return 1;
			}

			n = num/100;
			if(num%100)
				n++;

			if(!pay_from_treasury(n, "silver"))
				return 0;

			if(tmp = n*100 - num)
			{
				if(undefinedp(banghui_bank["coin"]))
					banghui_bank += ([ "coin" : tmp ]);
				else
					banghui_bank["coin"] += tmp;
			}

			return 1;
	}

	return 0;
}
