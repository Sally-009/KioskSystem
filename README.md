# KioskSystem

Date Created: 10/17/22 - 10/23/22
Description:

This program assumes a "Kiosk System" where the user makes an order and payment.
The flow is as follows:
1. Get menu data from input files divided based on the category of food.
2. Show the menu on the screen with its price.
3. If the item is sold out, show "Sold Out."
4. When the user makes an order, ask for quantity while reflecting its limited stock.
5. After the user finishes the order, go to check.
6. Select Chips and calculate the total.
7. Make a payment by input.
8. If the payment does not meet its required amount, ask them for the balance.
9. Finish!


アピールポイント
--------------

やることが多かったので、簡単なところからひとつづつ順序立てて作っていった。
最初はメニューの表示、そしてファイルのインプット、そして売り切れの処理を書き、最後に会計、及び注文の変更の処理を書いた。
出来るだけその関数で完結するように書いたことで、機能の後付けに対応できるようにした。注文の変更は一通り終わったあとにつけた機能であり、その心掛けが役に立った。
関数にするときも、あとでそのまま使う機会を想定し、出来るだけ一般的に、汎用的に使えるように書くことを意識した。
