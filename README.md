<h2>Executive Summary</h2>
<p>This project emulates the Unix command language Bash by utilizing proper threading technique to run any Bash commands in addition to the developer’s added commands in the krash.c file. Threads are ran independently from one another on the device’s scheduler, allowing for the ability to call commands in an executable program and direct standard output to a user specified file. This is a good starting point for building additional functions for a bash-like-hybrid.<p>
<h2>Installiation</h2>
<ol>
	<h4>For Ubuntu:</h4>
	<li>
		<p>Download branch <code>git clone https://github.com/cha-boy-nate/Krash.git</code></p>
	</li>
	<li>
		<p>Move to main folder<code>cd Krash</code></p>
	</li>
	<li>	
		<h5>For development:</h5>
		<p>Build executable<code>make</code></p>
	</li>
	<li>	
		<h5>For testing:</h5>
		<p>Run executable<code>./krash</code></p>
	</li>
</ol>
<h2>Background</h2>
Current built-in commands:
<ul>
<li>-help</li>
	<p>Prints the list of commands.</p>
<li>-pwd</li>
	<p>Prints the current word directory path.</p>
<li>-cd [dir]</li>
	<p>Changes directory to arguement.</p>
<li>-command > filename </li>
	<p>Executes command and outputs return value into the file.</p>
<li>-command</li>
	<p>Executes command.</p>
</ul>
