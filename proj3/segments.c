for(lli block_low = low_value; block_low < high_value; 
block_low += block_size + 2) {
	lli block_high = block_low + block_size;
	if(block_high > high_value) {
		block_high = high_value;
	}
	// sieve as before
}