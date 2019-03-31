
= エディタ「Lem」


LemはCommon Lispでほぼ全てが実装されたエディタです。



Common Lispでの拡張と、その開発環境を提供しています。 本書の執筆陣の過半がCommon Lispの開発にはLemを利用しているという実績から、ことCommon Lispの開発には必要十分な環境を提供できていると言えます。また、数はまだ少ないですが、Common Lisp以外の言語編集をサポートしています。
操作体系は作者がemacsを使っていたこともあり、emacsに似せてはいますが、切り替えて使えるvi(vim)のモードが用意されています。
本章では、3章以降で必要とされるLemのlispの開発/編集に関連した機能にしぼった紹介を行います。既にemacs等で環境を構築されている方は読みとばして問題ないと思います。Lemの用語や踏み込んだ解説については7章を参照ください。

== Lemのインストール


LemをインストールするにはRoswellを使うのが簡単です。
次のコマンドでインストールできます。


//emlist{
$ ros install cxxxr/lem
//}


Lemは256色をサポートしたターミナルで使うことを想定しています。
linuxのターミナルの場合、デフォルトでは8色しか表示できない事が多いのでTERM変数を変更してください。


//emlist{
$ export TERM=xterm-256color
//}

== キーバインドの表記について


LemではEmacsと同じようにControlやMetaをプリフィクスとするコマンドを使います。



@<b>{C-} コントロールキーを押しっぱなしにして別のキーを打つことを意味します。



@<b>{M-} メタキーを押しっぱなしにして別のキーを打つことを意味します。メタキーはAltキーを使い、Macのターミナルでは設定でOptionキーに割り当てられます。



たとえば
@<tt>{C-x o}はControlを押しながらxを押したあと、Controlを離してoを押します。
@<tt>{C-x C-o}だとControlを押しながらxを押し、更にControlを押しながらoを押します。

== Lemの起動と終了


コマンドラインからLemを起動するにはlemコマンドを使います。
lemコマンドはRoswellからインストールしている場合に使えます。


//emlist{
$ lem [ファイル名]
//}


終了するには@<tt>{C-x C-c}と入力してください。

== 基本的な使い方

ここでlispの開発の為に必要なLemの最小限の利用方法を説明します。

=== ファイルの編集

lemを起動したら新しいファイルを開いて編集しましょう。@<tt>{C-x C-f}と入力すると、画面下部にパスを入力する画面が表示されます。tabを押すと補完が効くので既存のディレクトリに移動するのも簡単です。入力が終わった所でreturnを押すとそのファイルを開きます。
編集が終わったら@<tt>{C-x C-s}で保存できます。

=== 複数のファイルの編集

@<tt>{C-x C-f}でファイルを開いた後に、@<tt>{C-x C-f}で別のファイルを開くことができます。複数ファイルを開いている時に、@<tt>{C-x b}を押すと、下部に@<tt>{Use Buffer:}と出て、ファイル名をしての編集するファイルの切り替えができます。全部キーボードで入力するのは大変なので、@<tt>{Tab}を押して@<tt>{↑},@<tt>{↓}で選択できます。編集を終了してファイルを閉じる際には@<tt>{C-x k}を使います。

=== 画面の分割

lemでは編集画面を分割することができます。現在の画面を@<tt>{C-x 2}で上下にふたつに、@<tt>{C-x 3}で左右にふたつに分割します。分割した時点でそれぞれの画面は同じファイルを編集中なので別のファイルを編集するには@<tt>{C-x b}を使います、カーソルがある画面を別の画面に移すには@<tt>{M-o}を使います。分割を解除する方法は@<tt>{C-x 0}で現在の画面、@<tt>{C-x 1}で現在の画面以外を削除します。

=== slime

Lemでのlispの開発支援をslimeと呼びます。slimeを起動するにはlem上で、@<tt>{M-x slime}と入力します。ウィンドウが分割され、@<tt>{CL-USER>}と表示された画面が表示されます。この画面をlispの世界ではreplと呼び、lispの式を打ち込むとその結果を返してくる機能を持っています。
コマンドプロンプトのようなものと思っていれば良いでしょう。@<tt>{10}のような数値を入力してreturnすると結果として@<tt>{10}が返ります。@<tt>{(+ 2 (* 3 4) 5)}のような少し複雑な式を入力すると@<tt>{19}のようにきちっと計算しているのがわかります。

コマンドプロンプトと同様replでも同じ式を何度も打ち込んだり、過去に打った式を編集してもう一度打ち込みたい時の為に履歴を参照することができます。普通のコマンドプロンプトでは履歴の参照は@<tt>{↑},@<tt>{↓}キーで行ないますが、lemのreplではカーソルが動いてしまいます。履歴の参照は@<tt>{↑}にあたるのが@<tt>{M-p},@<tt>{↓}にあたるのが、@<tt>{M-n}です。

replの画面はちょっとした式の入力(たとえば@<tt>{(loop for i to 100000 collect i)} など)で簡単に画面を埋めつくしてしまうことがあるため、消去したくなることがあります。@<tt>{C-c M-o} と入力すると散らかった画面を消すことができます。また、間違って決して終了しない式を入力してしまった際(たとえば、@<tt>{(loop while t :do (sleep 0))})に、 @<tt>{C-c C-c}を押すと式の実行を強制終了することができます。デバッガが立ち上がりますが、@<tt>{q}で終了させることができます。


=== lispファイルを編集中のキー操作
@<tt>{C-x C-f}で拡張子が@<tt>{.lisp}のファイルを開くとlisp用のキーがいくつか使えるようになります。ここでは便利なものを紹介します。

//table[lemlispmodekeytable][lispファイルのキー操作]{
キー  操作
------------
@<tt>{C-c C-e}  直前の式を評価する。
@<tt>{C-M-q}  直後の式をインデントする。
@<tt>{C-c z}  画面をreplに切り替える
//}

=== 困ったときは
ここまでで学んだことは必要最小限の内容なので、何かのはずみで本章で説明していない状態になって操作ができないと感じるようなことがあるかもしれません。そういう場合には、とりあえず@<tt>{C-g}を何回か押すと復帰できるので覚えておくと良いでしょう。全て保証できるわけではありませんが…

=== 本章で取り扱ったキー操作

//table[lemkeytable][2章でとりあげたlemのキー操作]{
キー  操作
------------
@<tt>{C-x C-c}  Lemの終了
@<tt>{C-x C-f}  ファイルを開く
@<tt>{C-x C-s}  変更の保存
@<tt>{C-x b}  編集対象の切り替え
@<tt>{C-x k}  編集の終了
@<tt>{C-x 0}  現在の画面の削除
@<tt>{C-x 1}  現在の画面以外を削除
@<tt>{C-x 2}  現在の画面を上下ふたつに分割
@<tt>{C-x 3}  現在の画面を左右ふたつに分割
@<tt>{M-o}  画面の移動
//}